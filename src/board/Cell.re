[@react.component]
let make = (~index, ~setPos, ~onClick, ~className="", ~w=20, ~h=20) =>
  <div
    onClick
    onMouseLeave={_ => setPos(None)}
    onMouseEnter={_ => setPos(index)}
    className={
      "bg-gray-200 border-red-400 border-2"
      ++ " w-"
      ++ string_of_int(w)
      ++ " h-"
      ++ string_of_int(h)
      ++ " "
      ++ className
    }
  />;
