open ShapeSelector;

open GridUtils;

open Constants;

module IntCmp =
  Belt.Id.MakeComparable({
    type t = int;
    let cmp = Pervasives.compare;
  });

module StrCmp =
  Belt.Id.MakeComparable({
    type t = string;
    let cmp = Pervasives.compare;
  });

let y =
  Belt_MapString.fromArray([|
    ("A", [|1, 4, 7|]),
    ("B", [|1, 4|]),
    ("C", [|4, 5, 7|]),
    ("D", [|3, 5, 6|]),
    ("E", [|2, 3, 6, 7|]),
    ("F", [|2, 7|]),
  |]);

let makeX = () => {
  let keys = y->Belt_MapString.keysToArray;
  let values =
    y
    ->Belt_MapString.valuesToArray
    ->flatten
    ->Belt_Set.fromArray(~id=(module IntCmp))
    ->Belt_Set.toArray;

  values
  ->Belt_Array.map(v =>
      (
        v,
        keys->Belt_Array.keep(k =>
          y
          ->Belt_MapString.get(k)
          ->Belt_Option.getWithDefault([||])
          ->includes(v)
        ),
      )
    )
  ->Belt_MapInt.fromArray;
};

// let solve = (rows: ) => {
