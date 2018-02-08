type action =
  | Change(string)
  | RemoveTagClick(string)
  | FocusClick
  | KeyPress(int);

type state = {
  tags: list(string),
  currentInput: string,
  inputRef: ref(option(Dom.element)),
  duplicateTag: string
};

let str = ReasonReact.stringToElement;

let component = ReasonReact.reducerComponent("TagsInput");

/* Check this link on refs to understand why we do This
   https://reasonml.github.io/reason-react/docs/en/react-ref.html */
let setInputRef = (r, {ReasonReact.state}) =>
  state.inputRef := Js.Nullable.to_opt(r);

/* This function helps as a step between the onChange handler and the actual reducer call.
   Its basically for putting ugly things like extracting input value, and letting the onChange handler
   and reducer clean */
let change = event =>
  Change(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

let keypress = event => KeyPress(ReactEventRe.Keyboard.which(event));

/* make is just a function that returns an object, which overrides the
   default component with whatever you pass after ...component  */
let make = (~onTagInput, ~onTagRemove, ~enableClearAll=false, _children) => {
  ...component,
  initialState: () => {
    tags: [],
    currentInput: "",
    inputRef: ref(None),
    duplicateTag: ""
  },
  /* pattern matching on the possible actions  */
  reducer: (action, state) =>
    switch action {
    | Change(text) =>
      ReasonReact.Update({...state, currentInput: text, duplicateTag: ""})
    | KeyPress(13) =>
      let exists = List.exists(t => t === state.currentInput, state.tags);
      if (! exists) {
        onTagInput(state.currentInput);
        ReasonReact.Update({
          ...state,
          tags: List.append(state.tags, [state.currentInput]),
          currentInput: ""
        });
      } else {
        let duplicate = List.find(t => t === state.currentInput, state.tags);
        ReasonReact.Update({...state, duplicateTag: duplicate});
      };
    | KeyPress(_) => ReasonReact.NoUpdate
    | RemoveTagClick(tag) =>
      onTagRemove(tag);
      ReasonReact.Update({
        ...state,
        tags: List.filter(t => t !== tag, state.tags)
      });
    | FocusClick =>
      switch state.inputRef^ {
      | None => ReasonReact.NoUpdate
      | Some(r) =>
        ReasonReact.SideEffects(ReactDOMRe.domElementToObj(r)##focus())
        |> ignore;
        ReasonReact.NoUpdate;
      }
    },
  render: ({reduce, state, handle}) =>
    <div>
      <div className="react-tags-input" onClick=(reduce((_) => FocusClick))>
        (
          List.map(
            tag =>
              <span
                key=tag
                className=(
                  "tag " ++ (state.duplicateTag === tag ? "duplicate" : "")
                )>
                (str(tag))
                <span
                  className="remove-tag"
                  onClick=(reduce((_) => RemoveTagClick(tag)))>
                  (str("X"))
                </span>
              </span>,
            state.tags
          )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
        <input
          _type="text"
          ref=(handle(setInputRef))
          value=state.currentInput
          onKeyPress=(reduce(keypress))
          onChange=(reduce(change))
        />
      </div>
      (enableClearAll ? <span> (str("clear all")) </span> : str(""))
    </div>
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~onTagInput=jsProps##onTagInput,
      ~onTagRemove=jsProps##onTagRemove,
      ~enableClearAll=jsProps##enableClearAll,
      [||]
    )
  );
