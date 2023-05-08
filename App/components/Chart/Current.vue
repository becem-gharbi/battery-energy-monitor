<template>
    <ChartBase :options="options">
    </ChartBase>
</template>

<script setup lang="ts">
const options = ref<HighchartsOptions>({
    title: {
        text: "Current"
    }
})
</script>