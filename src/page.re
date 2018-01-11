type action =
  | Change(string)
  | KeyPress(int);

let component = ReasonReact.reducerComponent("Page");

/* This function helps as a step between the onChange handler and the actual reducer call.
   Its basically for putting ugly things like extracting input value, and letting the onChange handler
   and reducer clean */
let change = event =>
  Change(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

let keypress = event => KeyPress(ReactEventRe.Keyboard.which(event));

/* make is just a function that returns an object, which overrides the
   default component with whatever you pass after ...component  */
let make = (~message, _children) => {
  ...component,
  initialState: () => "",
  /* pattern matching on the possible actions  */
  reducer: (action, state) =>
    switch action {
    | Change(text) => ReasonReact.Update(text)
    | KeyPress(int) =>
      switch int {
      | 13 =>
        Js.log("pressed Enter!");
        ReasonReact.NoUpdate;
      }
    },
  render: self =>
    <section>
      (ReasonReact.stringToElement(self.state))
      <div>
        <input
          _type="text"
          onKeyPress=(self.reduce(keypress))
          onChange=(self.reduce(change))
        />
      </div>
    </section>
};
