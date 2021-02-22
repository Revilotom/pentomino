open ShapeSelector;

open GridUtils;

open Constants;

open Belt_Array;

type coords = array((int, int));

type moveOption = {
  shapeId,
  orientations: array(coords),
};

module BlahComp =
  Belt.Id.MakeComparable({
    type t = array(int);

    let cmp = (arrA, arrB) => {
      arrA |> Array.sort((a, b) => a - b);
      arrB |> Array.sort((a, b) => a - b);

      let zipped = zip(arrA, arrB);
      let c = zipped->map(((a1, b1)) => Pervasives.compare(a1, b1));

      c->reduce(0, (acc, curr) => acc === 0 ? curr : acc);
    };
  });

let gridToPrint = range(0, 7)->map(row => range(row * 8, (row + 1) * 8 - 1));

let showCoords = (coords: coords) =>
  gridToPrint
  ->map(row =>
      row
      ->map(cell =>
          includes(centerCells, cell)
            ? "O"
            : coords
              ->getBy(x => coordsToindex(x) === cell)
              ->Belt_Option.isSome
                ? "@" : "-"
        )
      ->joinWith("", x => x)
    )
  ->joinWith("\n", x => x);

let getInitialOptions = () =>
  init->map(shape => {
    let rotations =
      make(4, shape)->mapWithIndex((i, x) => {...x, orientation: i * 90});
    let combined =
      concat(rotations, rotations->map(x => {...x, flipped: true}))
      ->map(shape =>
          toCoords(Some(shape), shape.orientation, shape.flipped)
          ->map(coordsToindex)
        )
      ->Belt.Set.fromArray(~id=(module BlahComp))
      ->Belt_Set.toArray;
    let orientations =
      combined->map(orientation =>
        orientation->map(index => indexToCoords(index))
      );

    {orientations, shapeId: shape.id};
  });

let rec getAllPositions =
        (options: array(moveOption), freePlaces: array(int)) => {
  let blah =
    options->map(opt =>
      {
        ...opt,
        orientations:
          opt.orientations
          ->map(coordinates => {
              let transformed =
                freePlaces->map(place =>
                  coordinates->map(coord =>
                    addCoords(coord, indexToCoords(place))
                  )
                );

              transformed->forEach(coords => {
                let grid = coords->showCoords;

                Js.log(coords);
                Js.log(grid);
                Js.log();
              });

              let validMoves =
                transformed->keep(coordindates =>
                  coordindates->every(coord => {
                    let (x, y) = coord;
                    includes(freePlaces, coordsToindex(coord))
                    && x > (-1)
                    && x < 8
                    && y > (-1)
                    && y < 8;
                  })
                );

              Js.log2("validMoves", validMoves);

              // Js.log(removeDuplicates->length);

              validMoves;
              // Js.log2(validMoves, opt.shapeId);
            })
          ->flatten
          ->map(orientation =>
              orientation->map(coord => coordsToindex(coord))
            )
          ->Belt.Set.fromArray(~id=(module BlahComp))
          ->Belt_Set.toArray
          ->map(orientation =>
              orientation->map(index => indexToCoords(index))
            ),
      }
    );
  blah;
};
