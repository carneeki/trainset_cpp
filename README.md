# trainset
A lathe gear change set calculator for lathes with an M/N * A/B * C/D style gearbox.

# How to Run:

These instructions are for Linux, but running on OS X will be identical. Running on Windows should be very similar.

Linux:
```
$ ./trainset
Usage: ./trainset <gear library> <output file> <M gear> <N gear> <pitch>
$
```

Windows:
` C:\Users\My Username\trainset.exe> <gear library> <output file> <M gear> <N gear> <pitch>`

# Explanation:
* ./trainset is the name of the command
* `<gear library>` is a file containing one number for each gear you have. In my library, I have 2x 32T gears, so I include the number 32 twice. The order is not important.
* `<output file>` is the name of a text file you want the trainset to save its output as.
* `<M gear>` The M gear.
* `<N gear>` The N gear. If you don't have M/N gears, just enter 1 and 1.
* `<pitch>` The pitch of your leadscrew in mm.

Example - My lathe is an L141 from Hare and Forbes in Australia. I created a gear library file for the ABCD gears (MN gears need to be treated separately for the moment), and the lathe has a 3mm pitch on the leadscrew.

`./trainset L141.lib.txt L141.28.35.out.txt 28 35 3`
