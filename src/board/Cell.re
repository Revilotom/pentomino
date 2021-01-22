open ShapeSelector;

type cell =
  | Empty
  | Center
  | HighlightValid
  | HighlightInvalid
  | HighLightPlaced
  | Placed(color);

let cellTypeToTailwind = (cellType: cell) =>
  switch (cellType) {
  | Empty => "bg-gray-200 border-red-400 border-2"
  | Center => "bg-gray-900 "
  | Placed(cellColor) => "bg-" ++ colorToString(cellColor) ++ "-500"
  | HighLightPlaced => "bg-orange-200"
  | HighlightValid => "bg-blue-200"
  | HighlightInvalid => "bg-red-300"
  };

[@react.component]
let make = (~index, ~setPos, ~onClick, ~cellType: cell, ~w=20, ~h=20) =>
  <div
    onClick
    onMouseLeave={_ => setPos(None)}
    onMouseEnter={_ => setPos(index)}
    className={
      " w-"
      ++ string_of_int(w)
      ++ " h-"
      ++ string_of_int(h)
      ++ " "
      ++ cellTypeToTailwind(cellType)
    }
  />;
