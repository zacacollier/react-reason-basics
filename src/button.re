let component = ReasonReact.statelessComponent "Button";

let make ::title ::handleClick _children => {
    ...component,
    render: fun _self =>
      <button onClick=(fun _event => handleClick ())> (ReasonReact.stringToElement title) </button>
};
