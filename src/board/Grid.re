open ShapeSelector;
open GridUtils;

type colorIndex = {
  color,
  indexes: array(int),
};

[@react.component]
let make =
    (
      ~selectedShape: option(shape),
      ~placedShapes: array(shape),
      ~placeShape,
    ) => {
  let (mousePos, setMousePos) = React.useState(() => None);

  let highlightedIndexes =
    getRelativeIndexes(mousePos, toCoords(selectedShape));

  let placedIndexes =
    placedShapes->Belt.Array.map(placedShape =>
      getRelativeIndexes(placedShape.cell, toCoords(Some(placedShape)))
    );

  <div className="flex justify-items-auto justify-center">
    <div
      className="justify-center h-full flex flex-wrap content-start  "
      style={ReactDOM.Style.make(~width="700px", ())}>
      {Array.make(64, None)
       |> Array.mapi((i, _) => {
            let combinedArray =
              Belt.Array.concat(
                placedIndexes->Belt.Array.reduce([||], (acc, curr) =>
                  Belt.Array.concat(acc, curr)
                ),
                highlightedIndexes,
              );
            let set = Belt.Set.Int.fromArray(combinedArray);
            let isValid =
              set->Belt.Set.Int.size === Array.length(combinedArray);

            <Cell
              className={
                highlightedIndexes->Belt.Array.some(x => x == i)
                  ? "bg-" ++ (isValid ? "blue" : "red") ++ "-200"
                  : "bg-"
                    ++ getPlacedShapeAtCell(i, placedShapes)
                       ->Belt.Option.map(x => colorToString(x.color))
                       ->Belt.Option.getWithDefault("")
                    ++ "-500"
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
            />;
          })
       |> React.array}
    </div>
  </div>;
};
