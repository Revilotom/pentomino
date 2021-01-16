[@react.component]
let make = () => {
  let (mousePos, setMousePos) = React.useState(() => None);

  <div className="flex justify-items-auto justify-center">
    <div
      className="justify-center h-full flex flex-wrap content-start  "
      style={ReactDOM.Style.make(~width="700px", ())}>
      {Array.make(64, None)
       |> Array.mapi((i, _) =>
            <Cell
              highlight={Some(i) === mousePos}
              index={Some(i)}
              setPos={x => setMousePos(_ => x)}
              key={string_of_int(i)}
            />
          )
       |> React.array}
    </div>
  </div>;
};
