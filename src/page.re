type action =
  | Change(string);

let component = ReasonReact.reducerComponent("Page");

let change = event =>
  Change(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

/* make is just a function that returns an object, which overrides the
   default component with whatever you pass after ...component  */
let make = (~message, _children) => {
  ...component,
  initialState: () => "",
  /* pattern matching on the possible actions  */
  reducer: (action, state) =>
    switch action {
    | Change(text) => ReasonReact.Update(text)
    },
  render: self =>
    <section>
      (ReasonReact.stringToElement(self.state))
      <div> <input _type="text" onChange=(self.reduce(change)) /> </div>
    </section>
};
