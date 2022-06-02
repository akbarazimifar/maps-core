// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "MapCore",
    platforms: [
        .iOS(.v11),
    ],
    products: [
        .library(
            name: "MapCore",
            targets: ["MapCore"]
        ),
        .library(
            name: "MapCoreSharedModule",
            targets: ["MapCoreSharedModule"]
        ),
        .library(
            name: "MapCoreSharedModuleCpp",
            targets: ["MapCoreSharedModuleCpp"]
        ),
    ],
    dependencies: [
        .package(name: "DjinniSupport",
                 url: "https://github.com/UbiqueInnovation/djinni.git",
                 .upToNextMajor(from: "1.0.0")),
    ],
    targets: [
        .target(
            name: "earcut",
            path: "external/earcut/",
            exclude: [
                "earcut/glfw",
                "earcut/test",
                "earcut/appveyor.yml",
                "earcut/CHANGELOG.md",
                "earcut/CMakeLists.txt",
                "earcut/LICENSE",
                "earcut/README.md",
            ],
            sources: [
                "",
                "earcut/include/",
                "earcut/include/mapbox/",
            ],
            publicHeadersPath: "earcut/include/mapbox/",
            cxxSettings: [
                .headerSearchPath("earcut/include/"),
                .headerSearchPath("earcut/include/mapbox/"),
            ]
        ),
        .target(
            name: "MapCore",
            dependencies: ["MapCoreSharedModule"],
            path: "ios",
            exclude: ["readme.md"],
            resources: [
                .process("graphics/Shader/Metal/"),
            ]
        ),
        .target(
            name: "MapCoreSharedModule",
            dependencies: ["DjinniSupport",
                           "MapCoreSharedModuleCpp"],
            path: "bridging/ios",
            publicHeadersPath: ""
        ),
        .target(
            name: "MapCoreSharedModuleCpp",
            dependencies: ["earcut"],
            path: "shared",
            sources: ["src"],
            publicHeadersPath: "public",
            cxxSettings: [
                .headerSearchPath("**"),
                .headerSearchPath("public"),
                .headerSearchPath("src/graphics"),
                .headerSearchPath("src/graphics/helpers"),
                .headerSearchPath("src/logger"),
                .headerSearchPath("src/map/camera"),
                .headerSearchPath("src/map/controls"),
                .headerSearchPath("src/map/coordinates"),
                .headerSearchPath("src/map/layers/objects"),
                .headerSearchPath("src/map/layers/icon"),
                .headerSearchPath("src/map/layers/line"),
                .headerSearchPath("src/map/layers/tiled"),
                .headerSearchPath("src/map/layers/tiled/raster"),
                .headerSearchPath("src/map/layers/tiled/wmts"),
                .headerSearchPath("src/map/scheduling"),
                .headerSearchPath("src/map"),
                .headerSearchPath("src/util"),
                .headerSearchPath("src/external/pugixml"),
                .define("DEBUG", to: "1", .when(configuration: .debug)),
                .define("NDEBUG", to: "1", .when(configuration: .release)),
            ]
        ),
    ],
    cxxLanguageStandard: .cxx1z
)
