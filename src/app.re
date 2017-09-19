[%bs.raw {|require('./app.css')|}];

module App = {
  type counter = int;

  type action =
    | Increment
    | IncrementOne int
    | CopyCounter int
    | ResetCounter int
    | ResetGlobal
    | NewCounter;

  type state = {
    count: int,
    counters: array int
  };

  let component = ReasonReact.reducerComponent "AppRe";

  let initialCount = 1;

  let incrementGlobal _event =>
    Increment;
  let newCounter _event =>
    NewCounter;
  let resetGlobal _event =>
    ResetGlobal;
  let incrementOne index _event =>
    IncrementOne index;
  let copyCounter index _event =>
    CopyCounter index;
  let resetCounter index _event =>
    ResetCounter index;

  let make _children => {

    ...component,

    initialState: fun () => {count: initialCount, counters: [|initialCount|]},

    reducer: fun action state =>
      switch action {

      | Increment => ReasonReact.Update {...state, count: state.count + 1}

      | IncrementOne index =>
        let counters = Array.copy state.counters;
        counters.(index) = counters.(index) + 1;
        ReasonReact.Update {...state, counters}

      | NewCounter =>
        let counters = Array.append state.counters [|initialCount|];
        ReasonReact.Update {...state, counters}

      | CopyCounter index =>
        let counters = Array.append state.counters [|state.counters.(index)|];
        ReasonReact.Update {...state, counters}

      | ResetCounter index =>
        let counters = Array.copy state.counters;
        counters.(index) = initialCount;
        ReasonReact.Update {...state, counters}

      | ResetGlobal =>
        let counters = Array.make (Array.length state.counters) initialCount;
        ReasonReact.Update {...state, counters}

      },

    render: fun {state, reduce} => {
      let counters =
        ReasonReact.arrayToElement (
          state.counters |>
          Array.mapi
            (
              fun index counter => {
                <Counter
                  key=(string_of_int index)
                  localValue=(("Local: " ^ string_of_int counter ^ "."))
                  globalValue=(("State: " ^ string_of_int state.count ^ "."))
                  handleResetGlobal=(reduce resetGlobal)
                  handleResetLocal=(reduce (resetCounter index))
                  handleIncrementLocal=(reduce (incrementOne index))
                  handleIncrementGlobal=(reduce incrementGlobal)
                  handleNew=(reduce newCounter)
                  handleCopy=(reduce (copyCounter index))
                  index=(index)
                />
              }
            )
        );
      <div className="App">
        <div className="App-header">
          counters
        </div>
      </div>
    }
  };
};
