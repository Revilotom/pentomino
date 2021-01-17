open ShapeSelector;
open GridUtils;

[@react.component]
let make =
    (
      ~selectedShape: option(shape),
      ~placedShapes: array(shape),
      ~placeShape,
    ) => {
  let (mousePos, setMousePos) = React.useState(() => None);

  let coords = toCoords(selectedShape);

  let relativeIndexes: array(int) =
    mousePos
    ->Belt.Option.map(pos =>
        coords
        |> Array.map(x => addCoords(x, indexToCoords(pos)))
        |> adjustCoords
        |> Array.map(coordsToindex)
      )
    ->Belt.Option.getWithDefault([||]);

  <div className="flex justify-items-auto justify-center">
    <div
      className="justify-center h-full flex flex-wrap content-start  "
      style={ReactDOM.Style.make(~width="700px", ())}>
      {Array.make(64, None)
       |> Array.mapi((i, _) =>
            <Cell
              onClick={_ =>
                selectedShape
                ->Belt.Option.flatMap(shape =>
                    mousePos->Belt.Option.map(cell =>
                      placeShape(shape.id, cell)
                    )
                  )
                ->Belt.Option.getWithDefault()
              }
              highlight={relativeIndexes->Belt.Array.some(x => x == i)}
              index={Some(i)}
              setPos={x => setMousePos(_ => x)}
              key={string_of_int(i)}
            />
          )
       |> React.array}
    </div>
  </div>;
};
