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

  let relativeIndexes =
    getRelativeIndexes(mousePos, toCoords(selectedShape));

  let placedIndexes: array(colorIndex) =
    placedShapes->Belt.Array.map(x =>
      {
        color: x.color,
        indexes: getRelativeIndexes(x.cell, toCoords(Some(x))),
      }
    );

  let getPlacedShape = (cell: int) => {
    placedIndexes
    ->Belt.Array.keep(x => x.indexes->Belt.Array.some(index => index === cell))
    ->Belt.Array.get(0);
  };

  <div className="flex justify-items-auto justify-center">
    <div
      className="justify-center h-full flex flex-wrap content-start  "
      style={ReactDOM.Style.make(~width="700px", ())}>
      {Array.make(64, None)
       |> Array.mapi((i, _) => {
            Js.log(getPlacedShape(i));
            <Cell
              className={
                relativeIndexes->Belt.Array.some(x => x == i)
                  ? "bg-blue-200"
                  : "bg-"
                    ++ getPlacedShape(i)
                       ->Belt.Option.map(x =>
                           switch (x.color) {
                           | Red => "red"
                           | Indigo => "indigo"
                           | Orange => "orange"
                           | Green => "green"
                           | Yellow => "yellow"
                           | Purple => "purple"
                           | Blue => "blue"
                           | Pink => "pink"
                           | Teal => "teal"
                           }
                         )
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
