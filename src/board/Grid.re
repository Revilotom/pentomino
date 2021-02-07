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
      ~orientation: int,
      ~setOrientation,
      ~setFlipped,
      ~flipped: bool,
    ) => {
  let (mousePos, setMousePos) = React.useState(() => None);

  let highlightedIndexes =
    getRelativeIndexes(
      mousePos,
      toCoords(selectedShape, orientation, flipped)->Belt_Set.toArray,
    );

  let placedCells: array(placedCells) =
    placedShapes
    ->Belt.Array.map(placedShape =>
        getRelativeIndexes(
          placedShape.cell,
          Belt_Set.toArray(
            toCoords(
              Some(placedShape),
              placedShape.orientation,
              placedShape.flipped,
            ),
          ),
        )
        ->Belt.Array.map(cell => {cell, shapeId: Some(placedShape.id)})
      )
    ->flatten;

  let invalidCells =
    placedCells->Belt.Array.concat(
      centerCells->Belt.Array.map(cell => {cell, shapeId: None}),
    );

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
            let isValid =
              !
                hasDuplicates(
                  Belt.Array.concat(
                    invalidCells->Belt.Array.map(x => x.cell),
                    highlightedIndexes,
                  ),
                );

            let hoveredPlacedCell =
              isValid
                ? hoveredPlacedCells->Belt.Array.getBy(x => x.cell == i) : None;

            let shapeAtThisCell = getPlacedShapeAtCell(i, placedShapes);
            let isHighlighted = includes(highlightedIndexes, i);
            let isCenter = includes(centerCells, i);

            <Cell
              cellType={
                Belt.Option.isSome(hoveredPlacedCell)
                  ? HighLightPlaced
                  : isHighlighted
                      ? isValid ? HighlightValid : HighlightInvalid
                      : (
                        switch (shapeAtThisCell) {
                        | Some(shape) => Placed(shape.color)
                        | None => isCenter ? Center : Empty
                        }
                      )
              }
              onClick={_ =>
                switch (selectedShape) {
                | Some(shape) =>
                  if (isValid) {
                    placeShape(Some(shape.id), Some(i));
                    setSelected(None);
                    setOrientation(0);
                    setFlipped(false);
                  }
                | None =>
                  hoveredPlacedCell->Belt.Option.forEach(placedCell => {
                    placeShape(placedCell.shapeId, None);
                    setSelected(placedCell.shapeId);
                    shapeAtThisCell->Belt.Option.forEach(shape => {
                      setOrientation(shape.orientation);
                      setFlipped(shape.flipped);
                    });
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
