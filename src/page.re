type action =
  | KeyPress(int);

type state = {tags: list(string)};

let component = ReasonReact.reducerComponent("Page");

let keypress = event => KeyPress(ReactEventRe.Keyboard.which(event));

/* make is just a function that returns an object, which overrides the
   default component with whatever you pass after ...component  */
let make = children => {
  ...component,
  initialState: () => {tags: [""]},
  /* pattern matching on the possible actions  */
  reducer: (action, state) =>
    switch action {
    /* pass the value */
    | KeyPress(int) =>
      switch int {
      | 13 =>
        Js.log("pressed Enter!");
        ReasonReact.NoUpdate;
      }
    },
  render: self =>
    <section>
      <div> <input _type="text" onKeyPress=(self.reduce(keypress)) /> </div>
    </section>
  /* (ReasonReact.stringToElement(self.state)) */
};
