-- PART 1

solve1 :: [Int] -> Int
solve1 (x:xs) =
  length $
  filter (\(a,b) -> a < b) $
  zip (x:xs) xs

readFileToList :: FilePath -> IO [Int]
readFileToList filePath = do
  content <- readFile filePath
  let fileLines = lines content
  let numbers = map read fileLines
  return numbers

main1 :: IO String
main1 =
  fmap show $
  fmap solve1 $
  readFileToList "input.txt"

-- PART 2

solve2 :: [Int] -> Int
solve2 (x:y:z) =
  solve1 $
  map (\(a,b,c) -> a + b + c) $
  zip3 (x:y:z) (y:z) z

main2 :: IO String
main2 =
  fmap show $
  fmap solve2 $
  readFileToList "input.txt"
