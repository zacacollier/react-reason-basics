let component = ReasonReact.statelessComponent "Counter";

let make
    ::localValue
    ::globalValue
    ::handleResetGlobal
    ::handleResetLocal
    ::handleIncrementLocal
    ::handleIncrementGlobal
    ::handleNew
    ::handleCopy
    ::index
    _children => {
  ...component,
  render: fun _self =>
    <div>
      <h2> (ReasonReact.stringToElement localValue) </h2>
      <Button handleClick=(fun _ => handleIncrementLocal index) title="Increment Local Count" />
      <Button handleClick=(fun _ => handleResetLocal index) title="Reset this counter" />
      <Button handleClick=(fun _ => handleResetGlobal ()) title="Reset ALL counters" />
      <Button handleClick=(fun _ => handleNew ()) title="New Counter" />
      <Button handleClick=(fun _ => handleCopy index) title="Duplicate counter" />
      <Button handleClick=(fun _ => handleIncrementGlobal ()) title="Increment Global Count" />
      <h2> (ReasonReact.stringToElement globalValue) </h2>
    </div>
};
