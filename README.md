# ds1052e
C program to control a Rigol DS1052E oscilloscope from a UNIX environment.

## Building

1. Clone the repository
2. Run `make`
3. Run `ds1052e` from where it is, or install it into your system in `/usr/local/bin`

## Usage

### Getting scope captures

Assuming `/dev/usbtmc1` is the scope:

`ds1052e /dev/usbtmc1 capture > capture.csv`

Scope captures are 600 datapoints. The program outputs data in CSV format. It looks like this:

```
-3.000000e-03,3.294118e+00
-2.990000e-03,3.309804e+00
-2.980000e-03,3.294118e+00
```

The first column is the timestamp in seconds, the second column is the first enabled channel.

### Getting measurement data

Assuming `/dev/usbtmc1` is the scope:

`ds1052e /dev/usbtmc1 measure`

The program outputs tab delimited data. It looks like this:

```
Vptp	3.040000e+00	8.000000e-04	
Vmax	3.040000e+00	2.000000e-04	
Vmin	0.000000e+00	-6.000000e-04	
Vavg	1.530000e+00	-1.620000e-04	
Vrms	2.130000e+00	2.000000e-04	
f	1.000000e+03	9.900000e+37	
T	1.000000e-03	9.900000e+37	
```

First column is the measurement name, the second column is the first enabled channel.
