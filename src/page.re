type action =
  | Change(string)
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
let change = event => {
  Js.log(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);
  Change(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);
};

let keypress = event => KeyPress(ReactEventRe.Keyboard.which(event));

/* make is just a function that returns an object, which overrides the
   default component with whatever you pass after ...component  */
let make = _children => {
  ...component,
  initialState: () => {tags: [""], currentInput: ""},
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
    },
  render: self =>
    <section>
      (str("Tags: "))
      (
        /* The pipe |> is a left-associative binary operator that's defined as a |> b == b(a). */
        /* This is how you render a list of strings*/
        List.map(tag => str(tag), self.state.tags)
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
      (str("Current Input: "))
      (str(self.state.currentInput))
      <div>
        <input
          _type="text"
          onKeyPress=(self.reduce(keypress))
          onChange=(self.reduce(change))
        />
      </div>
    </section>
};
