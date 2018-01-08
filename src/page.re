let component = ReasonReact.statelessComponent("Page");

let handleClick = (_event, _self) => Js.log("clicked!");

type person = {
  name: string,
  age: int,
  sex: string
};

let me = {name: "JP", age: 29, sex: "male"};

let isMorning = false;

Js.log(isMorning ? "Good morning!" : "Hello!");

let letsDestructure = (~person as {name}) => Js.log(name);

letsDestructure(~person=me);

/* Pattern matching  */
type payload =
  | BadResult(int)
  | GoodResult(string)
  | NoResult;

let data = GoodResult("Product shipped!");

let message =
  switch data {
  | GoodResult(theMessage) => "Success! " ++ theMessage
  | BadResult(errorCode) =>
    "Something's wrong. The error code is: " ++ string_of_int(errorCode)
  | NoResult => "Nothing"
  };

Js.log(message);

let make = (~message, _children) => {
  ...component,
  render: self =>
    <section onClick=(self.handle(handleClick))>
      (ReasonReact.stringToElement(message))
    </section>
};
