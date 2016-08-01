# ds1052e
Programs to control a Rigol DS1052E oscilloscope from a UNIX environment.

## Building

1. Clone the repository
2. Run `make`
3. Run the binaries from where they are, or install them into your system in /usr/local/bin

## Usage

### Getting scope captures

Assuming `/dev/usbtmc1` is the scope:

`get_capture /dev/usbtmc1 > capture.csv`

Scope captures are 600 datapoints. The program outputs data in CSV format. It looks like this:

```
-3.000000e-03,3.294118e+00
-2.990000e-03,3.309804e+00
-2.980000e-03,3.294118e+00
```

The first column is the timestamp in seconds, the second column is the first enabled channel.
