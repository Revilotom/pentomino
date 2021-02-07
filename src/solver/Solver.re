open Logic;
open ShapeSelector;

open GridUtils;

module PairSetComparator =
  Belt.Id.MakeComparable({
    type t =
      Belt_Set.t(
        PairComparator.PairComparator.t,
        PairComparator.PairComparator.identity,
      );

    let cmp = (a, b) => {
      Belt_Set.diff(a, b)->Belt_Set.size;
    };
  });

let solve = () => {
  let initialOptions =
    init->Belt.Array.map(shape => {
      let rotations =
        Belt.Array.make(4, shape)
        ->Belt.Array.mapWithIndex((i, x) => {...x, orientation: i * 90});
      let combined =
        Belt.Array.concat(
          rotations,
          rotations->Belt.Array.map(x => {...x, flipped: true}),
        )
        ->Belt.Array.map(shape =>
            toCoords(Some(shape), shape.orientation, shape.flipped)
          );
      //   print_string(combined)
      //   Js.log(combined);
      combined->Belt.Set.fromArray(~id=(module PairSetComparator));
    });
  ();

  Js.log(initialOptions->Belt_Array.map(Belt_Set.size));
};
