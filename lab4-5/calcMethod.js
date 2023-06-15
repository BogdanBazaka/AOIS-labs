import readFunc from '../readFunc.js';

export default function calcMethod(implicants, funcType, varMap) {
  const meanImplicants = [...implicants];
  implicants.forEach((curImplicant) => {
    for (let item of varMap) {
      const map = new Map([...item]);
      if (
        (funcType === "sdnf" && readFunc(curImplicant, map)) ||
        (funcType === "sknf" && !readFunc(curImplicant, map))
      ) {
        let vars = [...new Set(curImplicant.match(/[a-z]+/gi))];
        for (const key of map.keys()) {
          if (!vars.includes(key)) {
            map.set(key, key);
            break;
          }
        }
        let otherImplicants = implicants
          .slice(0, implicants.indexOf(curImplicant))
          .concat(implicants.slice(implicants.indexOf(curImplicant) + 1));
        if (
          otherImplicants.every(implicant => !implicant.includes(curImplicant))
          && curImplicant.length === 1
        ) break;
        let wholeImplicant = "";
        if (funcType === "sdnf") {
          otherImplicants.forEach((implicant) => {
            wholeImplicant += `(${implicant})+`;
          });
        } else if (funcType === "sknf") {
          otherImplicants.forEach((implicant) => {
            wholeImplicant += `(${implicant})*`;
          });
        }
        wholeImplicant = wholeImplicant.slice(0, -1);
        if (typeof readFunc(wholeImplicant, map) !== "string") {
          meanImplicants.splice(meanImplicants.indexOf(curImplicant), 1);
        }
        break;
      }
    }
  });
  if (funcType === "sdnf") return `(${meanImplicants.join(")+(")})`;
  else if (funcType === "sknf") return `(${meanImplicants.join(")*(")})`;
}