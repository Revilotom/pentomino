open ShapeSelector;

open GridUtils;

open Constants;

type columns = Belt_MapInt.t(array(Belt_MapString.key));

type rows = Belt_MapString.t(array(int));

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

let x = makeX();

let getSmallestCol = (columns: columns) =>
  columns
  ->Belt_MapInt.map(Belt_Array.length)
  ->Belt_MapInt.reduce(None, (acc, curK, curV) =>
      acc->Belt_Option.isNone
        ? Some((curK, curV))
        : acc->Belt_Option.map(v => {
            let (_, accV) = v;
            curV < accV ? (curK, curV) : v;
          })
    )
  ->Belt_Option.flatMap(((k, _)) => columns->Belt_MapInt.get(k));

let select = (rts: string, rows: rows, columns: columns) => {
  let cols = rows->Belt_MapString.get(rts)->Belt_Option.getWithDefault([||]);

  let selected =
    cols->Belt_Array.map(c =>
      (c, columns->Belt_MapInt.get(c)->Belt_Option.getWithDefault([||]))
    );

  let newColumns =
    columns
    ->Belt_MapInt.removeMany(cols)
    ->Belt_MapInt.map(row =>
        row->Belt_Array.keep(c =>
          !selected->Belt_Array.map(((_, cs)) => cs)->flatten->includes(c)
        )
      );

  (selected, newColumns);
};

let solve = (rows: rows, columns: columns) => {
  let smallestCol = getSmallestCol(columns);
  ();
};
