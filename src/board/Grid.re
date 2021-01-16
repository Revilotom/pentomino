[@react.component]
let make = () => {
  <div className="flex justify-items-auto justify-center">
    <div
      className="justify-center h-full  flex flex-wrap content-start  "
      style={ReactDOM.Style.make(~width="45%", ())}>
      {Array.make(64, None) |> Array.map(_ => <Cell />) |> React.array}
    </div>
  </div>;
};
