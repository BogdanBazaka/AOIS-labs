export function getSDNF(varMap, sets) {
  const indexes = [];
  sets.forEach((item, index) => {
    if (item.at(-1) == 1) indexes.push(index);
  });
  if (indexes.length === 0)
    return { result: "-", numForm: "-", indexForm: "-" };
  let result = "";
  indexes.forEach((index) => {
    result += "(";
    for (let key of varMap[index].keys()) {
      if (varMap[index].get(key) == 0) result += `!${key}`;
      else result += key;
      result += "*";
    }
    result = result.slice(0, -1);
    result += ")+";
  });
  return {
    result: result.slice(0, -1),
    numForm: `+(${indexes.map((index) => `${index}, `)}`.slice(0, -2) + ")",
    indexForm: indexForm(sets),
  };
}
  
export function getSKNF(varMap, sets) {
  const indexes = [];
  sets.forEach((item, index) => {
    if (item.at(-1) == 0) indexes.push(index);
  });
  let result = "";
  indexes.forEach((index) => {
    result += "(";
    for (let key of varMap[index].keys()) {
      if (varMap[index].get(key) == 1) result += `!${key}`;
      else result += key;
      result += "+";
    }
    result = result.slice(0, -1);
    result += ")*";
  });
  return {
    result: result.slice(0, -1),
    numForm: `*(${indexes.map((index) => `${index}, `)}`.slice(0, -2) + ")",
    indexForm: indexForm(sets),
  };
}

function indexForm(sets) {
  let result = [];
  sets.forEach(set => result.push(set.at(-1)));
  if (!result.includes(1)) return 0;
  result.forEach((elem, index, arr) => {
    arr[index] = elem * Math.pow(2, arr.length - 1 - index);
  });
  return result.reduce((sum, elem) => sum + elem);
}