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

Scope captures are 600 datapoints.
