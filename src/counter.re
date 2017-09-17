let component = ReasonReact.statelessComponent "Counter";

let make ::value ::onIncrement _children => {

  {
    ...component,

    render: fun _self =>
      <div>

        <Button onClick=onIncrement title="New" />
        <h2> (ReasonReact.stringToElement value) </h2>

      </div>

  }

};
