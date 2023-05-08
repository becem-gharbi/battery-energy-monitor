<template>
    <div>
        <ChartCurrent />
        <!-- <DataSelect v-if="!dataFiles" />

        <ul v-else>
            <li v-for="file of dataFiles"> {{ file.webkitRelativePath }}</li>
        </ul> -->
    </div>
</template>

<script setup lang="ts">
const dataFiles = useState<File[]>("data_files")

</script>