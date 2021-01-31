open Logic;
open ShapeSelector;

open GridUtils;

let solve = () => {
  let initialOptions =
    init->Belt.Array.map(shape => {
      let rotations =
        Belt.Array.make(4, shape)
        ->Belt.Array.mapWithIndex((i, x) => {...x, orientation: i * 90});
      Belt.Array.concat(
        rotations,
        rotations->Belt.Array.map(x => {...x, flipped: true}),
      )
      ->Belt.Array.reduce([||], (acc, cur) =>
          includes(
            acc->Belt.Array.map(x =>
              toCoords(Some(x), x.orientation, x.flipped)
            ),
            toCoords(Some(cur), cur.orientation, cur.flipped),
          )
            ? acc : Belt.Array.concat(acc, [|cur|])
        );
    });

  Js.log(initialOptions->Belt.Array.map(x => x->Belt.Array.map(y => y.id)));
  //   let rec nested = (remainingOptions: array(array(shape))) => {};
  //   ();
};
