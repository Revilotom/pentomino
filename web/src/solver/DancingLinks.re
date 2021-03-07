type dataObject = {
  up: dataObject,
  down: dataObject,
  left: dataObject,
  right: dataObject,
};

type columnObject = {
  up: dataObject,
  down: dataObject,
  left: columnObject,
  right: columnObject,
  rowCount: int,
};

let findLeastColumn = (col: columnObject) => {
  let res = ref(col);
  let smallestRowCount = ref(col.rowCount);
  let current = ref(col.right);

  while (current.contents !== col) {
    if (current.contents.rowCount < smallestRowCount.contents) {
      smallestRowCount := current.contents.rowCount;
      res := current.contents;
      current := current.contents.right;
    };
  };

  res;
};

let solve = (root: columnObject) =>
  if (root.right === root) {
    Js.log("solution");
  };
