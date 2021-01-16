[@react.component]
let make = () => {
  let (selected, setSelectedHandler) = React.useState(() => None);

  Js.log(selected);

  <div className="flex">
    <Grid />
    <div className="flex flex-wrap">
      <Shapes
        selected
        setSelected={(num: int) => setSelectedHandler(_ => Some(num))}
      />
    </div>
  </div>;
};
