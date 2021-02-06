open Logic;
open ShapeSelector;

open GridUtils;

module PairComparator =
  Belt.Id.MakeComparable({
    type t = array((int, int));

    let cmp = (a, b) => {
      let lengthOfMatchesInA =
        a
        ->Belt_Array.keep(((a1, a2)) =>
            b
            ->Belt_Array.getBy(((b1, b2)) => a1 === b1 && a2 === b2)
            ->Belt_Option.isSome
          )
        ->Belt_Array.length;

      let lengthOfMatchesInB =
        b
        ->Belt_Array.keep(((b1, b2)) =>
            a
            ->Belt_Array.getBy(((a1, a2)) => a1 === b1 && a2 === b2)
            ->Belt_Option.isSome
          )
        ->Belt_Array.length;

      lengthOfMatchesInA === a->Belt_Array.length
      && lengthOfMatchesInB === b->Belt_Array.length
        ? 0 : (-1);
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
      //   Js.log(combined);
      combined->Belt.Set.fromArray(~id=(module PairComparator));
    });
  ();
  //   let blah =
  //     initialOptions->Belt_Array.map(x =>
  //       x->Belt_Set.toArray->Belt_Array.forEach(y => Js.log(y))
  //     );
  //   ();
  //   Js.log(initialOptions->Belt_Array.map(Belt_Set.size));
  //   let rec nested = (remainingOptions: array(array(shape))) => {};
  //   ();
};
