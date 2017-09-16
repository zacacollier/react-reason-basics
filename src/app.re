[%bs.raw {|require('./app.css')|}];

type counter = int;

type action =
  | Increment
  | New;

type state = {
  count: int,
  counters: array int
};

let component = ReasonReact.reducerComponent "App";
let initialCount = 1;
let make _children => {

  ...component,

  initialState: fun () => {count: initialCount, counters: [|initialCount|]},

  reducer: fun action state =>
    switch action {
    | Increment => ReasonReact.Update {...state, count: state.count + 1}
    | New =>
      let counters = Array.append state.counters [|state.count|];
      ReasonReact.Update {...state, counters }
    },

  render: fun {state, reduce} => {
    let counters = ReasonReact.arrayToElement (Array.mapi
      (fun index counter => <h2 key=(string_of_int index)> (ReasonReact.stringToElement (string_of_int counter)) </h2>)
      state.counters
    );
    <div className="App">
      <div className="App-header">
        <Button onClick=(reduce (fun _event => Increment)) title="Increment" />
        <Button onClick=(reduce (fun _event => New)) title="New" />
        counters
      </div>
    </div>
  }

};
