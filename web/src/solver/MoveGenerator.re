open ShapeSelector;

open GridUtils;

open Constants;

open Belt_Array;

type coords = array((int, int));

type moveOption = {
  shape,
  positions: array(coords),
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
      ->map(s => {
          let coords = toCoords(Some(s), s.orientation, s.flipped);

          let minX = coords->reduce(0, (acc, (x, _)) => min(x, acc));
          let minY = coords->reduce(0, (acc, (_, y)) => min(y, acc));
          let xCorrection = minX < 0 ? - minX : 0;
          let yCorrection = minY < 0 ? - minY : 0;
          coords
          ->map(((x, y)) => (x + xCorrection, y + yCorrection))
          ->map(coordsToindex);
        })
      ->Belt.Set.fromArray(~id=(module BlahComp))
      ->Belt_Set.toArray;
    let orientations =
      combined->map(orientation =>
        orientation->map(index => indexToCoords(index))
      );
    {positions: orientations, shape};
  });

let getAllPositions =
    (
      options: array(moveOption),
      allPlaces: array(int),
      takenPlaces: array(int),
    ) =>
  options->map(opt =>
    {
      ...opt,
      positions:
        opt.positions
        ->map(coordinates =>
            allPlaces
            ->map(place =>
                coordinates->map(coord =>
                  addCoords(coord, place->indexToCoords)
                )
              )
            ->keep(coordindates =>
                coordindates->every(coord => {
                  let (x, y) = coord;
                  includes(allPlaces, coordsToindex(coord))
                  && !includes(takenPlaces, coordsToindex(coord))
                  && x > (-1)
                  && x < 8
                  && y > (-1)
                  && y < 8;
                })
              )
          )
        ->flatten
        ->map(orientation => orientation->map(coord => coordsToindex(coord)))
        ->Belt.Set.fromArray(~id=(module BlahComp))
        ->Belt_Set.toArray
        ->map(orientation => orientation->map(index => indexToCoords(index))),
    }
  );

let allPositions =
  getAllPositions(getInitialOptions(), range(0, 63), centerCells);
