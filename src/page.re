type action =
  | Change(string)
  | RemoveTagClick(string)
  | KeyPress(int);

type state = {
  tags: list(string),
  currentInput: string
};

let str = ReasonReact.stringToElement;

let component = ReasonReact.reducerComponent("Page");

/* This function helps as a step between the onChange handler and the actual reducer call.
   Its basically for putting ugly things like extracting input value, and letting the onChange handler
   and reducer clean */
let change = event =>
  Change(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

let keypress = event => KeyPress(ReactEventRe.Keyboard.which(event));

/* make is just a function that returns an object, which overrides the
   default component with whatever you pass after ...component  */
let make = _children => {
  ...component,
  initialState: () => {tags: [], currentInput: ""},
  /* pattern matching on the possible actions  */
  reducer: (action, state) =>
    switch action {
    | Change(text) => ReasonReact.Update({...state, currentInput: text})
    | KeyPress(13) =>
      ReasonReact.Update({
        tags: List.append(state.tags, [state.currentInput]),
        currentInput: ""
      })
    | KeyPress(_) => ReasonReact.NoUpdate
    | RemoveTagClick(tag) =>
      ReasonReact.Update({
        ...state,
        tags: List.filter(t => t !== tag, state.tags)
      })
    },
  render: ({reduce, state}) =>
    <section>
      <div className="react-tags-input">
        (
          List.map(
            tag =>
              <span key=tag className="tag">
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
          value=state.currentInput
          onKeyPress=(reduce(keypress))
          onChange=(reduce(change))
        />
      </div>
    </section>
};
