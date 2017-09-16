let component = ReasonReact.statelessComponent "Button";

let make ::title ::onClick _children => {
  let click event => onClick title;
  {
    ...component,
    render: fun _self =>
      <button onClick=click> (ReasonReact.stringToElement title) </button>
  }
};
