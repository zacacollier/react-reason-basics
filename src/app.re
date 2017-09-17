[%bs.raw {|require('./app.css')|}];

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

let component = ReasonReact.reducerComponent "App";

let initialCount = 1;

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
      let counters = Array.append state.counters [|state.count|];
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
    let renderEl e => ReasonReact.stringToElement e;
    let counters =
      ReasonReact.arrayToElement (
        Array.mapi
          (
            fun index counter =>
              <h2 key=(string_of_int index)>

                ("Local: " ^ string_of_int counter ^ "." |> renderEl)

                <button onClick=(reduce (fun _ => IncrementOne index))>
                  (renderEl "Increment Local Count")
                </button>

                <button onClick=(reduce (fun _ => ResetCounter index))>
                  (renderEl "Reset this counter")
                </button>

                <button onClick=(reduce (fun _ => ResetGlobal))>
                  (renderEl "Reset ALL counters")
                </button>

                <button onClick=(reduce (fun _ => NewCounter))>
                  (renderEl "new counter")
                </button>

                <button onClick=(reduce (fun _ => CopyCounter index))>
                  (renderEl "duplicate counter")
                </button>

                <button onClick=(reduce (fun _ => Increment))>
                  (renderEl "Increment Global Count")
                </button>

                ("State: " ^ string_of_int state.count ^ "." |> renderEl)

              </h2>
          )
          state.counters
      );
    <div className="App"> <div className="App-header"> counters </div> </div>
  }
};
