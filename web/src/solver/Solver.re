open ShapeSelector;

open GridUtils;

open Constants;

type map = Belt_MapString.t(array(string));

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

let makeColumns = (rows: map) => {
  let keys = rows->Belt_MapString.keysToArray;
  let values =
    rows
    ->Belt_MapString.valuesToArray
    ->flatten
    ->Belt_Set.fromArray(~id=(module StrCmp))
    ->Belt_Set.toArray;
  values
  ->Belt_Array.map(v =>
      (
        v,
        keys->Belt_Array.keep(k =>
          rows
          ->Belt_MapString.get(k)
          ->Belt_Option.getWithDefault([||])
          ->includes(v)
        ),
      )
    )
  ->Belt_MapString.fromArray;
};

let getSmallestCol = (columns: map) =>
  columns
  ->Belt_MapString.map(Belt_Array.length)
  ->Belt_MapString.reduce(None, (acc, curK, curV) =>
      acc->Belt_Option.isNone
        ? Some((curK, curV))
        : acc->Belt_Option.map(v => {
            let (_, accV) = v;
            curV < accV ? (curK, curV) : v;
          })
    )
  ->Belt_Option.flatMap(((k, _)) => columns->Belt_MapString.get(k));

let select = (rts: string, rows: map, columns: map) => {
  let cols = rows->Belt_MapString.get(rts)->Belt_Option.getWithDefault([||]);

  let selected =
    cols
    ->Belt_Array.map(c =>
        columns->Belt_MapString.get(c)->Belt_Option.getWithDefault([||])
      )
    ->flatten;

  columns
  ->Belt_MapString.removeMany(cols)
  ->Belt_MapString.map(row =>
      row->Belt_Array.keep(c => !selected->includes(c))
    );
};

let rec solveHelper =
        (rows: map, columns: map, solution: array(string))
        : array(array(string)) =>
  // Js.log(columns->Belt_MapInt.toArray);
  if (columns->Belt_MapString.size === 0) {
    Js.log("solution");
    Js.log(solution);

    // raise(Not_found);

    [|solution|];
  } else {
    getSmallestCol(columns)
    ->Belt_Option.getWithDefault([||])
    ->Belt_Array.map(r =>
        solveHelper(
          rows,
          select(r, rows, columns),
          solution->Belt_Array.concat([|r|]),
        )
      )
    ->flatten;
  };

let solve = (rows: map, columns: map) => solveHelper(rows, columns, [||]);
