<template>
    <ChartBase :options="options" />
</template>

<script setup lang="ts">

const props = defineProps<{ measurements?: Measurements }>()

const options = computed<HighchartsOptions>(() => ({
    chart: {
        zooming: {
            type: "x"
        }
    },
    title: {
        text: "Measurements"
    },
    xAxis: {
        type: 'datetime',
        dateTimeLabelFormats: {
            millisecond: '%H:%M:%S',
            second: '%H:%M:%S',
            minute: '%H:%M',
            hour: '%H:%M',
            day: '%e. %b',
            week: '%e. %b',
            month: '%b \'%y',
            year: '%Y'
        },
    },
    series: [{
        name: "Current",
        type: 'line',
        data: props.measurements?.current
    }, {
        name: "Voltage",
        type: 'line',
        data: props.measurements?.voltage
    }, {
        name: "Power",
        type: 'line',
        data: props.measurements?.power
    }]
}))
</script>