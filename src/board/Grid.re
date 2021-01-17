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

  let relativeIndexes =
    getRelativeIndexes(mousePos, toCoords(selectedShape));

  let placedIndexes =
    placedShapes->Belt.Array.map(x =>
      getRelativeIndexes(x.cell, toCoords(Some(x))) |> Array.to_list
    )
    |> Array.to_list
    |> List.flatten;

  <div className="flex justify-items-auto justify-center">
    <div
      className="justify-center h-full flex flex-wrap content-start  "
      style={ReactDOM.Style.make(~width="700px", ())}>
      {Array.make(64, None)
       |> Array.mapi((i, _) =>
            <Cell
              className={
                relativeIndexes->Belt.Array.some(x => x == i)
                  ? "bg-blue-200"
                  : placedIndexes->Belt.List.some(x => x == i)
                      ? "bg-red-500" : ""
              }
              onClick={_ =>
                selectedShape
                ->Belt.Option.flatMap(shape =>
                    mousePos->Belt.Option.map(cell =>
                      placeShape(shape.id, cell)
                    )
                  )
                ->Belt.Option.getWithDefault()
              }
              index={Some(i)}
              setPos={x => setMousePos(_ => x)}
              key={string_of_int(i)}
            />
          )
       |> React.array}
    </div>
  </div>;
};
