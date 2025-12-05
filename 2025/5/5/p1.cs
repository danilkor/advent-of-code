// var lines = File.ReadAllLines("../../../input.txt").ToList();
//
//
// List<(long, long)> Ranges = new List<(long, long)>();
// foreach (var line in lines)
// {
//     if (line.Trim() == "")
//     {
//         break;
//     }
//
//     var Parts = line.Split("-").ToList().Select((s => Int64.Parse(s))).ToList();
//     Ranges.Add((Parts[0],Parts[1]));
// }
//
// int ok = 0;
// foreach (var line in lines)
// {
//     if (line.Contains("-") || line.Trim() == "")
//     {
//         continue;
//     }
//     foreach (var range in Ranges)
//     {
//         var number = Int64.Parse(line);
//         if (number <= range.Item2 && number >= range.Item1)
//         {
//             ok++;
//             break;
//         }
//     }
// }
//
// Console.WriteLine(ok);