export default function getConstituents(snf) {
  const constituents = [];
  let constituent = "";
  snf.split("").forEach((item) => {
    if (item !== "(") {
      if (item === ")") {
        constituents.push(constituent);
        constituent = "";
      } else constituent += item;
    } else constituent = "";
  });
  return constituents;
}