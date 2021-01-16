[@react.component]
let make = () => {
  let (selected, setSelected) = React.useState(() => None);

  Js.log(selected);

  <div> <Grid /> <Shapes setSelected /> </div>;
};
