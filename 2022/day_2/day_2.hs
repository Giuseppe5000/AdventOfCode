-- PART 1

solve1 :: Int -> Int -> [(String, Int)] -> Int
solve1 hor depth [] = hor*depth
solve1 hor depth (x:xs)
  | a == "forward" = solve1 (hor + b) depth xs
  | a == "down" = solve1 hor (depth + b) xs
  | a == "up" = solve1 hor (depth - b) xs
  where
    a = fst x
    b = snd x

dataFormatter :: [[String]] -> [(String, Int)]
dataFormatter x = map (\(a:b:_) -> (a,read b)) x

readFileToList :: FilePath -> IO [[String]]
readFileToList filePath = do
  content <- readFile filePath
  let fileLines = lines content
  let fileData = map words fileLines
  return fileData

main1 :: IO String
main1 =
  fmap show $
  fmap (solve1 0 0) $
  fmap dataFormatter $
  readFileToList "input.txt"

-- PART 2

solve2 :: Int -> Int -> Int -> [(String, Int)] -> Int
solve2 aim hor depth [] = hor*depth
solve2 aim hor depth (x:xs)
  | a == "forward" = solve2 aim (hor + b) (depth + aim * b) xs
  | a == "down" = solve2 (aim + b) hor depth xs
  | a == "up" = solve2 (aim - b) hor depth xs
  where
    a = fst x
    b = snd x

main2 :: IO String
main2 =
  fmap show $
  fmap (solve2 0 0 0) $
  fmap dataFormatter $
  readFileToList "input.txt"
