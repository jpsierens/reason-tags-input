let component = ReasonReact.statelessComponent("Page");

let handleClick = (_event, _self) => Js.log("clicked!");

type person = {
  name: string,
  age: int,
  sex: string
};

let me = {name: "JP", age: 29, sex: "male"};

Js.log(me);

let make = (~message, _children) => {
  ...component,
  render: self =>
    <section onClick=(self.handle(handleClick))>
      (ReasonReact.stringToElement(message))
    </section>
};
