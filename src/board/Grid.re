open ShapeSelector;

[@react.component]
let make = (~selectedShape: option(shape)) => {
  let (mousePos, setMousePos) = React.useState(() => None);

  let coords =
    switch (selectedShape) {
    | Some(selectedShape) =>
      switch (selectedShape.id) {
      | 0 => [|(0, 1), (1, 0), (1, 1), (1, 2), (2, 0)|]
      | 1 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
      | 2 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
      | 3 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
      | 4 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
      | 5 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
      | 6 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
      | 7 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
      | 8 => [|(0, 0), (0, 1), (0, 2), (0, 3), (0, 4)|]
      | _ => [||]
      }
    | None => [||]
    };

  let valid =
    coords->Belt.Array.keep(((x, y)) => x >= 0 && x <= 7 && y >= 0 && y <= 7)
    |> Array.length === Array.length(coords);

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
