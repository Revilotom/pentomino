open ShapeSelector;
open GridUtils;

type placedCells = {
  cell: int,
  shapeId: option(shapeId),
};

[@react.component]
let make =
    (
      ~selectedShape: option(shape),
      ~placedShapes: array(shape),
      ~placeShape,
      ~setSelected,
    ) => {
  let (mousePos, setMousePos) = React.useState(() => None);

  let highlightedIndexes =
    getRelativeIndexes(mousePos, toCoords(selectedShape));

  let placedIndexes =
    placedShapes->Belt.Array.map(placedShape =>
      getRelativeIndexes(placedShape.cell, toCoords(Some(placedShape)))
    );

  let placedCells: array(placedCells) =
    placedShapes
    ->Belt.Array.map(placedShape =>
        getRelativeIndexes(placedShape.cell, toCoords(Some(placedShape)))
        ->Belt.Array.map(cell => {cell, shapeId: Some(placedShape.id)})
      )
    ->Belt.Array.reduce([||], (acc, curr) => Belt.Array.concat(acc, curr));

  let hoveredPlacedCells =
    mousePos
    ->Belt.Option.flatMap(pos =>
        placedCells
        ->Belt.Array.getBy(x => x.cell === pos)
        ->Belt.Option.map(shape =>
            placedCells->Belt.Array.keep(c => c.shapeId === shape.shapeId)
          )
      )
    ->Belt.Option.getWithDefault([||]);

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

            let hoveredPlacedCell =
              hoveredPlacedCells->Belt.Array.getBy(x => x.cell == i);

            <Cell
              className={
                Belt.Option.isSome(hoveredPlacedCell)
                  ? "   bg-orange-100"
                  : highlightedIndexes->Belt.Array.some(x => x == i)
                      ? "bg-" ++ (isValid ? "blue" : "red") ++ "-200"
                      : "bg-"
                        ++ getPlacedShapeAtCell(i, placedShapes)
                           ->Belt.Option.map(x => colorToString(x.color))
                           ->Belt.Option.getWithDefault("")
                        ++ "-500"
              }
              onClick={_ =>
                switch (selectedShape) {
                | Some(shape) =>
                  if (isValid) {
                    placeShape(Some(shape.id), Some(i));
                    setSelected(None);
                  }
                | None =>
                  hoveredPlacedCell->Belt.Option.forEach(placedCell => {
                    placeShape(placedCell.shapeId, None);
                    setSelected(placedCell.shapeId);
                  })
                }
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
