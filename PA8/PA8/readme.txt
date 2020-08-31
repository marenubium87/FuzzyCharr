Explanation of algorithm for Task 4:

Take an example array of signed integers:

We assume the array has at least one negative element.  We will
check for this at the beginning of the program.  If the array
does not contain at least one negative element, then the task
reduces to finding the lowest valued single element in the array
and will not be discussed further here.

Index:	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
Value:	7	1	-2	-5	3	8	-9	-4	5	-7	6	-4	-1	2	-8	11

We notice that we can trim any subsequence of positive numbers
on the left and right ends of the array, since their inclusion
onto the ends of any other subarray would certain increase
the sum, instead of decreasing it.

So excising all positive values at the ends, we can set the left
and right bounds to the portion of the array we wish to focus
our efforts on, thus.

Index:	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
Value:	7	1	-2	-5	3	8	-9	-4	5	-7	6	-4	-1	2	-8	11
Marker:			LB												RB

****THIS DOESN'T WORK
i.e.
Index	0-99	100	101	102
Value	-1		100	100	-4

My algorithm would focus on the -4 and then never "get over" to the
other valley of the -1s.

MUST CONSOLIDATE ALL NEGATIVE AND POSITIVE SECTIONS FOR THIS TO WORK!

Then inside our subarray, locate the most negative element and
mark it.  From here forward we will omit the elements in the 
array outside the bounds for brevity.

Index:	2	3	4	5	6	7	8	9	10	11	12	13	14
Value:	-2	-5	3	8	-9	-4	5	-7	6	-4	-1	2	-8
Marker:	LB				^								RB

WLOG we will focus on how the rightward portion of this algorithm
will be conducted.  The leftward portion is exactly analogous
to the rightward portion.

First, move the marker one element to the right for as long as the 
value of the element there is negative, as for any negative value 
we can simply just incorporate it into the subarray to achieve
a lower sum.

Index:	6	7	8	9	10	11	12	13	14
Value:	-9	-4	5	-7	6	-4	-1	2	-8
Marker:	^	R1					
Bounds: [	]

Next, for every location where the value of the element is negative
but the subsequent element is positive, set a marker there and add
all of the elements from the previous marker to the new marker, and
see if the result is negative.

Index:	6	7	8	9	10	11	12	13	14
Value:	-9	-4	5	-7	6	-4	-1	2	-8
Marker:	^	R1		R2			
Bounds: [	]
Adding:			5	-7  = -2

If the result is in fact negative, incorporate those elements into
the subarray, for it results in a lower total sum.

Index:	6	7	8	9	10	11	12	13	14
Value:	-9	-4	5	-7	6	-4	-1	2	-8
Marker:	^			R2			
Bounds: [			]

Repeat the process.  If we find that the result is not negative for
any given valid location of the marker (i.e. where the element is
negative but the subsequent element is positive), we move on
without doing anything.

Index:	6	7	8	9	10	11	12	13	14
Value:	-9	-4	5	-7	6	-4	-1	2	-8
Marker:	^			R2			R3		
Bounds: [			]
Adding:					6	-4	-1 = 1 > 0 (do nothing)

We continue doing this until we reach the right bound as originally set,
which is guaranteed to be a location where the element is negative but
the subsequent element is positive, by design.

Index:	6	7	8	9	10	11	12	13	14
Value:	-9	-4	5	-7	6	-4	-1	2	-8
Marker:	^			R2					R3		
Bounds: [			]
Adding:					6	-4	-1	2	-8	= -5 (negative!)

Index:	6	7	8	9	10	11	12	13	14
Value:	-9	-4	5	-7	6	-4	-1	2	-8
Marker:	^								R3		
Bounds: [								]

Note that if the 14th element had been, say, -1, resulting in a sum
of the last 5 elements of 2, we simply would have left the right bound
at the R2 marker position and called it a day.

We would now repeat the exact same process going to the left, until
we hit the original left bound


-2 1 -4 37 -4 1 -5

i:	0	1	2	3	4	5	6
	-1	4	-6	37	-4	1	-5
	[]  ^						start: 0 end: 0 sum: -1	<- min

i:	0	1	2	3	4	5	6
	-1	4	-6	37	-4	1	-5
			[]  ^				start: 2 end: ? sum: -6

