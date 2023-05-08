<template>
    <div class="max-w-sm flex flex-col justify-center items-center gap-4">
        <img src="~/assets/images/select-data.svg">

        <input hidden ref="inputRef" type="file" webkitdirectory multiple />

        <n-button class="w-fit" type="primary" @click="() => inputRef?.click()">
            <template #icon>
                <NaiveIcon name="ph:folder-duotone" :size="23"></NaiveIcon>
            </template>
            Select data folder
        </n-button>
    </div>
</template>

<script setup lang="ts">
const inputRef = ref<HTMLInputElement>()

const sessions = useState<Session[]>("sessions")
const settings = useState<Settings>("settings")

function handleSettings(file?: File) {

    if (!file) {
        throw new Error("Settings file not found")
    }

    const reader = new FileReader();

    reader.readAsText(file);

    reader.onload = function () {
        if (reader.result) {
            const data = JSON.parse(reader.result.toString());

            settings.value = {
                debug: data["debug"],
                sampleRate: data["sampleRate"],
                savingRate: data["savingRate"],
                currentGain: data["currentGain"],
                currentOffset: data["currentOffset"],
                voltageGain: data["voltageGain"],
                voltageOffset: data["voltageOffset"]

            }
        }
    };
}

function handleSessions(files?: File[]) {
    sessions.value = files?.reverse() || []
}

onMounted(() => {
    inputRef.value?.addEventListener("change", (event) => {

        //@ts-ignore
        const files: File[] = Object.values(event.target?.files)

        const settingsFile = files.find(el => el.webkitRelativePath.endsWith("settings.json") && el.type === "application/json")

        handleSettings(settingsFile)

        const sessionsFiles = files.filter(el => el.webkitRelativePath.includes("sessions") && el.type === "text/csv")

        handleSessions(sessionsFiles)
    })
})

</script>