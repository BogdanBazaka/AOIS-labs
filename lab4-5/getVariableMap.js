export default function getVariableMap(variables, sets) {
  const varMap = [];
  sets.forEach((set) => {
    let varObj = new Map();
    variables.forEach((variable, index) => {
      varObj.set(variable, set[index]);
    });
    varMap.push(varObj);
  });
  return varMap;
}