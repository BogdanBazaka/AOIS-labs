export default function generateTruthTableVariables(variablesCount) {
  const truthTableVariables = [];
  for (let i = 0; i < 2 ** variablesCount; i++) {
    truthTableVariables.push(
      Array.from(
        { length: variablesCount },
        (_, j) => Math.floor(i / 2 ** (variablesCount - 1 - j)) % 2
      )
    );
  }
  return truthTableVariables;
}