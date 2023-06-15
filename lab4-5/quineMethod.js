import generateTruthTableVariables from "../generateTruthTableVariables.js";

export default function quineMethod(variables, constituentsStr, implicantsStr) {
  const constituents = {
    constituents: constituentsStr,
    variables: getVariables(constituentsStr, variables),
  };
  const implicants = {
    implicants: implicantsStr,
    variables: getVariables(implicantsStr, variables),
    covering: [],
  };

  implicants.variables.forEach((implicantVars) => {
    let coveredConstituents = [];
    constituents.variables.forEach((constituent, constituentIndex) => {
      if (implicantVars.every((elem) => constituent.includes(elem))) {
        coveredConstituents.push(constituentIndex);
      }
    });
    implicants.covering.push(coveredConstituents);
  });

  const constituentIndexes = constituents.variables.map((elem, index) => index);

  const table = generateTruthTableVariables(implicants.covering.length);
  const coverSets = [];
  table.forEach((set) => {
    let coveredIndexes = [];
    set.forEach((pos, posIndex) => {
      if (pos) coveredIndexes += implicants.covering[posIndex];
    });
    if (constituentIndexes.every((elem) => coveredIndexes.includes(elem))) {
      coverSets.push(set);
    }
  });
  const minSet = coverSets[0];
  coverSets.forEach((set) => {
    if (
      minSet.reduce((accumulator, currentValue) => accumulator + currentValue, 0) >
      set.reduce((accumulator, currentValue) => accumulator + currentValue, 0)
    ) minSet = set;
  });
  
  const mnf = [];
  minSet.forEach((pos, index) => {
    if (pos) mnf.push(implicants.implicants[index]);
  });
  return mnf[0][1] === "+" || mnf[0][2] === "+"
    ? "(" + mnf.join(")*(") + ")"
    : "(" + mnf.join(")+(") + ")";
}

function getVariables(array, variables) {
  return array.map((implicant) => {
    let vars = [];
    implicant.split("").forEach((elem, index, arr) => {
      if (variables.includes(elem)) {
        if (arr[index - 1] === "!") vars.push("!" + elem);
        else vars.push(elem);
      }
    });
    return vars;
  });
};