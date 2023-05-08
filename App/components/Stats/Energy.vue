<template>
    <n-statistic label="Energy exchanged" tabular-nums>
        <n-number-animation ref="value" :from="0" :to="measurements?.energy" active :precision="0.1" :duration="3000" />
        <template #suffix>
            Wh
        </template>
    </n-statistic>
</template>

<script setup lang="ts">
defineProps<{ measurements?: Measurements }>()
</script>