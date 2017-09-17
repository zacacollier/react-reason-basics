let component = ReasonReact.statelessComponent "Button";

let make ::title ::onClick _children => {
  let click _event => onClick;
  {
    ...component,
    render: fun _self =>
      <button onClick=click> (ReasonReact.stringToElement title) </button>
  }
};
