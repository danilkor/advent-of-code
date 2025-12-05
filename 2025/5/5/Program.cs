var lines = File.ReadAllLines("../../../test.txt").ToList();
List<(long, long)> Ranges = new List<(long, long)>();

long sum = 0;

// ⌨️ parse input
foreach (var line in lines)
{
    if (line.Trim() == "")
    {
        // 🪹 Empty line
        break;
    }

    var Parts = line.Split("-").ToList().Select((s => Int64.Parse(s))).ToList();
    Ranges.Add((Parts[0],Parts[1]));
}

// Check overlapping ranges ⭕⭕

List<List<(long, long)>> IterRanges = new List<List<(long, long)>>();
IterRanges.Add(Ranges);
bool overlap = true;

// 🔁 Repeat until all computed all overlaps
while (overlap)
{
    overlap = false;
    var Currange = IterRanges.Last();
    var NewRanges = new List<(long, long)>(); // We can't change list we are looping through, so we create a new 🆕 one
    (long, long)? RangeNotToAdd = null;
    for (var i = 0; i < Currange.Count; i++)
    {
        var range1 = Currange[i];
        bool current_overlap = false;
        if (!overlap)
        {
            for (var j = i + 1; j < Currange.Count; j++)
            {
                var range2 = Currange[j];
                if ((range1.Item1 <= range2.Item2 && range2.Item1 <= range1.Item2) || // See if any overlap
                    (range2.Item1 <= range1.Item2 && range1.Item1 <= range2.Item2))
                {
                    Console.WriteLine("Overlap"); // Debug print
                    current_overlap = true;
                    overlap = true;
                    var start = range1.Item1 > range2.Item1 ? range2.Item1 : range1.Item1;
                    var end = range1.Item2 > range2.Item2 ? range1.Item2 : range2.Item2;

                    NewRanges.Add((start, end));
                    RangeNotToAdd = range2;
                }
                
                // We already found overlap                
                if (current_overlap)
                {
                    break;
                }
            }
        }

        // We already found overlap
        if (current_overlap)
        {
            continue;
        }

        if (overlap && range1 != RangeNotToAdd)
        {
            NewRanges.Add(range1);
        }
        else if (!overlap)
        {
            NewRanges.Add(range1);
        }
    }

    IterRanges.Add(NewRanges);
}

long answer = 0;

foreach (var range in IterRanges.Last())
{
    answer += range.Item2 - range.Item1 + 1;
}

Console.WriteLine(answer);
